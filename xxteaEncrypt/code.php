<?php
/**
* 把一个文件夹里的文件全部转码
* @param string $filename 文件夹路径
* @param string $output_encoding  转换后的编码
* 网址：http://www.jscto.net/html/530.html
* 技术交流QQ群：287546175
*/
function change_code($filename,$output_encoding){
	if(file_exists($filename)){
		//如果是目录，采用递归继续转换
		if(is_dir($filename)){
			foreach (glob("$filename/*") as $key=>$value){
				change_code($value,$output_encoding);
			}
		}else{
			$contents_before = file_get_contents($filename);;
			$code = mb_detect_encoding($contents_before, array('ASCII','GB2312','GBK','UTF-8'));
			$contents_after = iconv($code,$output_encoding,$contents_before);
			file_put_contents($filename, $contents_after);
		}
	}else{
		echo '参数错误';
		return false;
	}
}
change_code('./test','utf-8');
echo "success!";
?>