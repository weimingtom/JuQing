<?php

define('DS', DIRECTORY_SEPARATOR);
define('BIN_DIR', rtrim(dirname(dirname(__DIR__)), '/\\'));
ini_set("memory_limit", "512M");
if (DS == '/')
{
    define('LUAJIT_BIN', 'luajit');
}
else
{
    define('LUAJIT_BIN', BIN_DIR . '\\win32\\luajit.exe');
}
define('XXTEA_PATH', dirname(__FILE__).DS);
require_once(XXTEA_PATH.'/xxtea.php');

$options = array(
    array('h',   'help',       0,      false,       'show help'),
    array('i',   'src',        1,      null,        'source files directory'),
    array('o',   'output',     1,      null,        'output filename | output directory'),
    array('p',   'prefix',     1,      '',          'package prefix name'),
    array('x',   'excludes',   1,      null,        'excluded packages'),
    array('m',   'pack',    1,      'files',       'pack mode'),
    #array('e',   'encrypt',    1,      null,        'encrypt mode'),
    array('ek',  'key',        1,      null,        'encrypt key'),
    array('es',  'sign',       1,      null,        'encrypt sign'),
    #array('ex',  'extname',    1,      'pb',       'encrypted file extension name (default is "lua"), only valid for xxtea_chunk'),
    array('c',   'config',     1,      null,        'load options from config file'),
    array('q',   'quiet',      0,      false,       'quiet'),
);

function errorhelp()
{
    print("\nshow help:\n    pack_files -h\n\n");
}
function help()
{
    global $options;

    echo <<<EOT

usage: pack_files -i src -o output ...

options:

EOT;

    for ($i = 0; $i < count($options); $i++)
    {
        $o = $options[$i];
        printf("    -%s %s\n", $o[0], $o[4]);
    }

    echo <<<EOT

pack mode:
    -m zip                  package all files to a ZIP archive file and encrypt.
    -m files (default)  save encrypted files to separate files. -o specifies output dir.
                        * default encrypt sign is "XXTEA"

config file format:

    return array(
        'src'      => source files directory,
        'output'   => output filename or output directory,
        'prefix'   => package prefix name,
        'excludes' => excluded packages,
        'pack'  => pack mode,
        'key'      => encrypt key,
        'sign'     => encrypt sign,
    );

examples:

    # encrypt res/*.* to resnew/, with XXTEA, specifies sign
    pack_files -i res -o resnew -ek XXTEA -es tsts

    # package res/*.* to game.zip
    pack_files -i res -o game.zip -m zip

    # package scripts/*.* to game.zip, encrypt game.zip with XXTEA, specifies sign
    pack_files -i scripts -o game.zip -m zip -ek XXTEA -es tsts

    # load options from config file
    pack_files -c my_config.lua


EOT;
}

// helper functions
function fetchCommandLineArguments($arg, $options, $minNumArgs = 0)
{
    if (!is_array($arg) || !is_array($options))
    {
        print("ERR: invalid command line arguments");
        return false;
    }

    $config = array();
    $newOptions = array();
    for ($i = 0; $i < count($options); $i++)
    {
        $option = $options[$i];
        $newOptions[$option[0]] = $option;
        $config[$option[1]] = $option[3];
    }
    $options = $newOptions;

    $i = 1;
    while ($i < count($arg))
    {
        $a = $arg[$i];
        if ($a{0} != '-')
        {
            printf("ERR: invalid argument %d: %s", $i, $a);
            return false;
        }

        $a = substr($a, 1);
        if (!isset($options[$a]))
        {
            printf("ERR: invalid argument %d: -%s", $i, $a);
            return false;
        }

        $key = $options[$a][1];
        $num = $options[$a][2];
        $default = $options[$a][3];

        if ($num == 0)
        {
            $config[$key] = true;
        }
        else
        {
            $values = array();
            for ($n = 1; $n <= $num; $n++)
            {
                $values[] = $arg[$i + $n];
            }
            if (count($values) == 1)
            {
                $config[$key] = $values[0];
            }
            else
            {
                $config[$key] = $values;
            }
        }

        $i = $i + $num + 1;
    }

    return $config;
}


function convertConfigValueToString($value)
{
    if (is_null($value))
    {
        return null;
    }
    else if (is_array($value))
    {
        foreach ($value as $k => $v)
        {
            $value[$k] = convertConfigValueToString($v);
        }
    }
    else if (is_string($value))
    {
        return '"' . $value . '"';
    }
    else
    {
        return (string)$value;
    }
}

function getScriptFileBytecodes($path, $tmpfile)
{
    if (!file_exists($path))
    {
        printf("ERR: cannot read Lua source file %s\n", $path);
        return false;
    }

    if (file_exists($tmpfile))
    {
        if (!unlink($tmpfile))
        {
            printf("ERR: cannot remove tmp file %s\n", $tmpfile);
            return false;
        }
    }

    @mkdir(pathinfo($tmpfile, PATHINFO_DIRNAME), 0777, true);
    $command = sprintf('%s -b -s "%s" "%s"', LUAJIT_BIN, $path, $tmpfile);
    passthru($command);

    if (!file_exists($tmpfile))
    {
        printf("ERR: cannot compile file %s\n", $path);
        return false;
    }

    return file_get_contents($tmpfile);
}

//
class FilesPacker
{
    const COMPILE_ZIP = 'zip';
    const COMPILE_FILES = 'files';
    const COMPILE_C = 'c';
    #const ENCRYPT_XXTEA_ZIP = 'xxtea_zip';
    #const ENCRYPT_XXTEA_CHUNK = 'xxtea_chunk';
    const ENCRYPT_XXTEA_DEFAULT_SIGN = 'XXTEA';

    private $config;
    private $options;
    private $validated = false;

    function __construct($config, $options)
    {
        $this->config = $config;
        $this->options = $options;
    }
	
	function myfunction1($value) {
                return trim($value);
            }
	function myfunction2($value) {
		return !empty($value);
	}
			
    function validateConfig()
    {
        if (empty($this->config['src']))
        {
            printf("ERR: not specifies source files directory\n");
            return false;
        }

        if (empty($this->config['output']))
        {
            printf("ERR: not output filename or output directory\n");
            return false;
        }

        if (!empty($this->config['prefix']))
        {
            $this->config['prefix'] = $this->config['prefix'] . '.';
        }
        else
        {
            $this->config['prefix'] = '';
        }

        if (!empty($this->config['excludes']))
        {
            $excludes = explode(',', $this->config['excludes']);
            array_walk($excludes, "myfunction1");
            $this->config['excludes'] = array_filter($excludes, "myfunction2");
        }
        else
        {
            $this->config['excludes'] = array();
        }

        if ($this->config['pack'] != self::COMPILE_ZIP
            && $this->config['pack'] != self::COMPILE_FILES
            && $this->config['pack'] != self::COMPILE_C
            )
        {
            printf("ERR: invalid pack mode %s\n", $this->config['pack']);
            return false;
        }

        #if (!empty($this->config['encrypt'])
        #    && $this->config['encrypt'] != self::ENCRYPT_XXTEA_ZIP
        #    && $this->config['encrypt'] != self::ENCRYPT_XXTEA_CHUNK)
        #{
        #    printf("ERR: invalid encrypt mode %s\n", $this->config['encrypt']);
        #    return false;
        #}

        #if (!empty($this->config['encrypt']) && empty($this->config['key']))
        #{
        #    print("ERR: not set encrypt key\n");
        #    return false;
        #}

        #if ($this->config['encrypt'] == self::ENCRYPT_XXTEA_ZIP
        #    || $this->config['encrypt'] == self::ENCRYPT_XXTEA_CHUNK)
        {
            #if (($this->config['pack'] == self::COMPILE_FILES || $this->config['pack'] == self::COMPILE_C)
            #    && $this->config['encrypt'] != self::ENCRYPT_XXTEA_CHUNK)
            #{
            #    print("ERR: pack mode \"files\" or \"c\" must use encrypt mode \"xxtea_chunk\"\n");
            #    return false;
            #}

            if (empty($this->config['sign']))
            {
                $this->config['sign'] = self::ENCRYPT_XXTEA_DEFAULT_SIGN;
            }
        }

        #if (!empty($this->config['encrypt']) && empty($this->config['sign']))
        #{
        #    print("ERR: not set encrypt sign\n");
        #    return false;
        #}

        #if (empty($this->config['extname']))
        #{
        #    print("ERR: not specifies encrypted file extension name\n");
        #    return false;
        #}

        if (!$this->config['quiet'])
        {
            $this->dumpConfig($this->config, $this->options);
        }

        // check src path
        $srcpath = realpath($this->config['src']);
        if (!is_dir($srcpath))
        {
            printf("ERR: invalid src dir %s\n", $srcpath);
            return false;
        }
        $this->config['srcpath'] = $srcpath;
        $this->config['srcpathLength'] = strlen($srcpath) + 1;

        if ($this->config['pack'] == self::COMPILE_ZIP)
        {
            if (is_dir($this->config['output']))
            {
                printf("ERR: output file is dir %s\n", $this->config['output']);
                return false;
            }
        }
        else if ($this->config['pack'] == self::COMPILE_FILES)
        {
            @mkdir($this->config['output'], 0777, true);
            $this->config['output'] = realpath($this->config['output']);
            if (empty($this->config['output']) || !is_dir($this->config['output']))
            {
                printf("ERR: invalid output dir %s\n", $this->config['output']);
                return false;
            }
        }

        $this->validated = true;
        return true;
    }

    function run()
    {
        if (!$this->validated)
        {
            print("ERR: invalid config\n");
            return false;
        }

        $files = $this->searchSourceFiles();
        $modules = $this->prepareForPack($files);

        #if ($this->config['encrypt'] == self::ENCRYPT_XXTEA_CHUNK)
        {
            $bytes = $this->getModulesData($modules, $this->config['key'], $this->config['sign']);
        }
        #else
        #{
        #    $bytes = $this->getModulesData($modules);
        #}
        if (!is_array($bytes))
        {
            $this->cleanupTempFiles($modules);
            return false;
        }

        if (!$this->createOutput($modules, $bytes))
        {
            $this->cleanupTempFiles($modules);
            return false;
        }

        $this->cleanupTempFiles($modules);
        return true;
    }

    protected function searchSourceFiles()
    {
        if (!$this->config['quiet'])
        {
            printf("Pack source files in path %s\n", $this->config['srcpath']);
        }
        $files = array();
        $this->findFiles($this->config['srcpath'], $files);
        return $files;
    }

    protected function prepareForPack(array $files)
    {
        $modules = array();
        // prepare for pack
        foreach ($files as $key => $path)
        {
           # if (substr($path, -4) != '.lua')
            #{
            #    unset($files[$key]);
            #}
           # else
            {
                #$moduleName = substr(substr($path, $this->config['srcpathLength']), 0, -4);
                $moduleName = substr($path, $this->config['srcpathLength']);
                $moduleName = str_replace('.', SPLIT_CHAR, $moduleName);
                $tempFilePath = $this->config['srcpath'] . DS . $moduleName . '.tmp';
                $moduleName = str_replace(DS, '.', $moduleName);
                $skip = false;

                foreach ($this->config['excludes'] as $key => $exclude)
                {
                    if (substr($moduleName, 0, strlen($exclude)) == $exclude)
                    {
                        unset($files[$key]);
                        $skip = true;
                        break;
                    }
                }

                if ($skip) continue;

                $bytesName = 'lua_m_' . strtolower(str_replace(array('.', '-'), '_', $moduleName));

                $modules[$path] = array(
                    'moduleName' => $moduleName,
                    'tempFilePath' => $tempFilePath,
                    'bytesName' => $bytesName,
                );
            }
        }
        return $modules;
    }

    protected function cleanupTempFiles(array $modules)
    {
        foreach ($modules as $module)
        {
            if (file_exists($module['tempFilePath']))
            {
                unlink($module['tempFilePath']);
            }
        }
    }

    protected function getModulesData(array $modules, $key = null, $sign = null)
    {
        if (!empty($key))
        {
            $xxtea = new XXTEA();
            $xxtea->setKey($key);
        }

        $modulesBytes = array();
        foreach ($modules as $path => $module)
        {
            $bytes = file_get_contents($path);
			/*$contents_before = file_get_contents($path);
			$code = mb_detect_encoding($contents_before, array('ASCII','GB2312','GBK','UTF-8'));
			$contents_after = iconv($code,$output_encoding,$contents_before);
			file_put_contents($filename, $contents_after);*/
			//$code = mb_detect_encoding($bytes, array('ASCII','GB2312','GBK','UTF-8'));
			//$bytes = iconv($code,'UTF-8',$bytes);
            /*if (!empty($key))
            {
                $bytes = $sign . $xxtea->encrypt($bytes);
            }*/
            file_put_contents($module['tempFilePath'], $bytes);
            if (!$bytes)
            {
                print("\n");
                return false;
            }
            $modulesBytes[$path] = $bytes;
            if (!$this->config['quiet'])
            {
                printf("  > get bytes [% 3d KB] %s\n", ceil(strlen($bytes) / 1024), $module['moduleName']);
            }
        }
        return $modulesBytes;
    }

    protected function createOutputZIP(array $modules, array $bytes)
    {
        // create ZIP archive
        $zipfile = $this->config['output'];
        $zip = new ZipArchive();
        if (!$zip->open($zipfile, ZIPARCHIVE::OVERWRITE | ZIPARCHIVE::CM_STORE))
        {
            return false;
        }

        if (!$this->config['quiet'])
        {
            printf("create ZIP archive file: %s\n", $zipfile);
        }
        foreach ($modules as $path => $module)
        {
            #$zip->addFromString($this->config['prefix'] . str_replace(SPLIT_CHAR, '.', $module['moduleName']) , $bytes[$path]);
            $zip->addFromString($this->config['prefix'] . str_replace(SPLIT_CHAR, '.', str_replace('.', DS, $module['moduleName'])) , $bytes[$path]);
        }
        $zip->close();

        if (!empty($this->config['key']))
        {
            $xxtea = new XXTEA();
            $xxtea->setKey($this->config['key']);
            file_put_contents($zipfile, $this->config['sign'] . $xxtea->encrypt(file_get_contents($zipfile)));
        }
        if (!$this->config['quiet'])
        {
            printf("done.\n\n");
        }
        return true;
    }

    protected function createOutputC(array $modules, array $bytes)
    {
        // create C source file
        $cfile = $this->config['output'];
        if (!$this->config['quiet'])
        {
            printf("create C source file: %s\n", $cfile);
        }

        $path = $this->config['output'];
        $pi = pathinfo($path);
        $hfile = $pi['dirname'] . DS . $pi['filename'] . '.h';
        $outputSourceBasename = $pi['filename'];
        $outputHeaderFilename = $outputSourceBasename . '.h';
        $outputSourceFilename = $pi['basename'];

        // create source file
        $contents = array();
        $contents[] = <<<EOT

/* ${outputSourceFilename} */

#include "lua.h"
#include "lauxlib.h"
#include "${outputHeaderFilename}"

EOT;

        foreach ($modules as $path => $module)
        {
            $contents[] = sprintf('/* %s */', $module['moduleName']);
            $contents[] = sprintf('static const char %s[] = {', $module['bytesName']);
            $contents[] = $this->encodeBytesToString($bytes[$path]);
            $contents[] = '};';
            $contents[] = '';
        }

        $contents[] = '';

        foreach ($modules as $module)
        {
            $functionName = 'luaopen_' . $module['bytesName'];
            $bytesName = $module['bytesName'];
            $moduleName = $module['moduleName'];

            $contents[] = <<<EOT

int ${functionName}(lua_State *L) {
    luaL_loadbuffer(L,
                    (const char*)${bytesName},
                    sizeof(${bytesName}),
                    "${moduleName}");
    return 1;
}

EOT;
        }

        $contents[] = '';
        $contents[] = "static luaL_Reg ${outputSourceBasename}_modules[] = {";

        foreach ($modules as $module)
        {
            $contents[] = sprintf('    {"%s", %s},', $module["moduleName"], 'luaopen_' . $module['bytesName']);
        }

        $contents[] = <<<EOT
    {NULL, NULL}
};

void luaopen_${outputSourceBasename}(lua_State* L)
{
    luaL_Reg* lib = ${outputSourceBasename}_modules;
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    for (; lib->func; lib++)
    {
        lib->func(L);
        lua_setfield(L, -2, lib->name);
    }
    lua_pop(L, 2);
}

EOT;

        if (!file_put_contents($cfile, implode("\n", $contents)))
        {
            return false;
        }


        // create header file
        if (!$this->config['quiet'])
        {
            printf("create C header file: %s\n", $hfile);
        }

        $headerSign = '__LUA_MODULES_' . strtoupper(md5($outputSourceBasename . time())) . '_H_';
        $outputHeaderFilename = basename($outputHeaderFilename);

        $contents = array();
        $contents[] = <<<EOT

/* ${outputHeaderFilename}.h */

#ifndef ${headerSign}
#define ${headerSign}

#if __cplusplus
extern "C" {
#endif

#include "lua.h"

void luaopen_${outputSourceBasename}(lua_State* L);

EOT;

        $contents[] = '/*';
        foreach ($modules as $module)
        {
            $contents[] = sprintf('int %s(lua_State* L);', 'luaopen_' . $module['bytesName']);
        }
        $contents[] = '*/';

        $contents[] = <<<EOT

#if __cplusplus
}
#endif

#endif /* ${headerSign} */

EOT;

        if (!file_put_contents($hfile, implode("\n", $contents)))
        {
            return false;
        }


        if (!$this->config['quiet'])
        {
            printf("done.\n\n");
        }
        return true;
    }

    protected function createOutputFiles(array $modules, array $bytes)
    {
        foreach ($modules as $module)
        {
            $destPath = $this->config['output'] . DS . str_replace(SPLIT_CHAR, '.', str_replace('.', DS, $this->config['prefix'] . $module['moduleName']));
            @mkdir(pathinfo($destPath, PATHINFO_DIRNAME), 0777, true);
            rename($module['tempFilePath'], $destPath);
        }

        printf("create output files in %s .\n", $this->config['output']);
        print("done.\n\n");
        return true;
    }

    protected function createOutput(array $modules, array $bytes)
    {
        if ($this->config['pack'] == self::COMPILE_ZIP)
        {
            return $this->createOutputZIP($modules, $bytes);
        }
        #else if ($this->config['pack'] == self::COMPILE_C)
        #{
        #    return $this->createOutputC($modules, $bytes);
        #}
        else if ($this->config['pack'] == self::COMPILE_FILES)
        {
            return $this->createOutputFiles($modules, $bytes);
        }
        else
        {
            printf("ERR: pack mode %s not implemented\n", $this->config['pack']);
            return false;
        }
    }


//    function dump($outputFileBasename)
//    {

//
//### HOW TO USE ###
//
//1. Add code to AppDelegate.cpp:
//
//    extern "C" {
//    #include "${outputFileBasename}.h"
//    }
//
//2. Add code to AppDelegate::applicationDidFinishLaunching()
//
//    CCScriptEngineProtocol* pEngine = CCScriptEngineManager::sharedManager()->getScriptEngine();
//    luaopen_${outputFileBasename}(pEngine->getLuaState());
//
//    pEngine->executeString("require(\"main\")");
//
//
//EOT;
//        }
//
//    }
//
//
    private function encodeBytesToString($bytes)
    {
        $len      = strlen($bytes);
        $contents = array();
        $offset   = 0;
        $buffer   = array();

        while ($offset < $len)
        {
            $buffer[] = ord(substr($bytes, $offset, 1));
            if (count($buffer) == 16)
            {
                $contents[] = '    ' . $this->encodeBytesToStringBlock($buffer);
                $buffer = array();
            }
            $offset++;
        }
        if (!empty($buffer))
        {
            $contents[] = '    ' . $this->encodeBytesToStringBlock($buffer);
        }

        return implode("\n", $contents);
    }

    private function encodeBytesToStringBlock($buffer)
    {
        $output = array();
        $len = count($buffer);
        for ($i = 0; $i < $len; $i++)
        {
            $output[] = sprintf('0x%02x,', $buffer[$i]);
        }
        return implode('', $output);
    }
	
	
	function dumpConfig($config, $options)
	{
		print("config:\n");
		for ($i = 0; $i < count($options); $i++)
		{
			$key = $options[$i][1];
			$value = convertConfigValueToString($config[$key]);
			if ($value != null)
			{
				printf("    %s = %s\n", $key, $value);
			}
		}
		print("\n");
	}
	function findFiles($dir, array & $files)
	{
		$dir = rtrim($dir, "/\\") . DS;
		$dh = opendir($dir);
		if ($dh == false) return;

		while (($file = readdir($dh)) !== false)
		{
			if ($file{0} == '.') { continue; }

			$path = $dir . $file;
			if (is_dir($path))
			{
				$this->findFiles($path, $files);
			}
			elseif (is_file($path))
			{
				$files[] = $path;
			}
		}
		closedir($dh);
	}
}

// ------------------------------------------------------------------------------------------------
print("\n");
if ($argc < 2)
{
    help();
    return(1);
}

$config = fetchCommandLineArguments($argv, $options, 4);
if (!$config)
{
    errorhelp();
    return(1);
}

if ($config['help'])
{
    help();
    return(0);
}

if ($config['config'])
{
    $configFilename = $config['config'];
    if (file_exists($configFilename))
    {
        $config = @include($configFilename);
    }
    else
    {
        $config = null;
    }

    if (!is_array($config))
    {
        printf("ERR: invalid config file, %s\n", $configFilename);
        errorhelp();
        return(1);
    }
}

$packer = new FilesPacker($config, $options);
if ($packer->validateConfig())
{
    return($packer->run());
}
else
{
    errorhelp();
    return(1);
}