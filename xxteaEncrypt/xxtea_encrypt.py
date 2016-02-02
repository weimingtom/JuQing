import platform
import os,sys,re
import zipfile
import time
#xxtea_encrypt.bat -i Resources0 -o Resources -ek topwo2015juqing -es topwo
#xxtea_encrypt.sh -i Resources0 -o Resources -ek pyy2015 -es topwo
#xxtea_encrypt.py -i Resources0 -o Resources -ek pyy2015 -es topwo
#php "./lib/FilesPacker.php" -i Resources0 -o Resources -ek topwo -es topwo
ignoreFolders = ('Music','shaders','SoundEffect','Flash','Document\\Music','Document\\Equips\\audio',
	'UI\\MusicBloom','Document\\flash','Document\\Audition','MusicPlayer\\project_for_background','MusicPlayer\\project_for_plist','MusicPlayer\\shaders')
ignoreZips = ('ShopMusic',)

ek = 'topwo'
es = 'topwo'
phpcommand = 'php "{0}/pack_files.php" -i {1} -o {2} -ek {3} -es {4}'
regex = '^({0}|{0}\\\w*)$'

slash = ''
if platform.system() == 'Windows':
	slash = '\\'
elif platform.system() == 'Linux':
	slash = '/'

def curPath():
	path = sys.path[0]
	if os.path.isdir(path):
		return path
	elif os.path.isfile(path):
		return os.path.dirname(path)

def getRealPath(path):
	items = path.split(slash)
	realItems = []
	for item in items:
		if item == '..':
			if len(realItems)>0:
				realItems.pop()
			else:
				print 'illegal path'
		elif item == '':
			break
		else:
			realItems.append(item)
	return slash.join(realItems)

def zipFolder(path,name):
	f = zipfile.ZipFile(name,'w',zipfile.ZIP_DEFLATED)
	for dirpath, dirnames, filenames in os.walk(path):
		for filename in filenames:
			if filename.find('.zip') < 0:
				f.write(os.path.join(dirpath,filename))
	f.close()

def isIgnoreZips(filename):
	for z in ignoreZips:
		if filename.find(z) >= 0:
			return True
	return False

def isIgnoreFolder(foldname,ignorelist):
	foldarr = foldname.split('\\')
	for ig in ignorelist:
		isignore = True
		ignorearr = ig.split('\\')
		minlen = min(len(foldarr),len(ignorearr))
		if cmp(foldarr[0:minlen],ignorearr[0:minlen]) == 0:
			return True
	return False

def getEffectivePathsAndZipPaths(rootPath):
	effectivePaths = []
	zipFiles = []
	for dirpath,dirnames,filenames in os.walk(rootPath):
		suffix = dirpath[len(rootPath)+1:]
		if len(suffix) > 0 and not isIgnoreFolder(suffix,ignoreFolders):
			for filename in filenames:
				if filename.find('.zip') >=0 and not isIgnoreZips(filename):
					zipfilename = os.path.join(dirpath,filename)
					if zipfilename not in zipFiles:
						zipFiles.append(zipfilename)			
			effectivePaths.append(dirpath)
	return effectivePaths,zipFiles

def main():
	rootPath = getRealPath(curPath() + "\\olddir")
	tmpPath = getRealPath(curPath() + "\\tmp")

	if not os.path.exists(tmpPath):
		os.system('md ' + tmpPath)

	effectivePaths,zipFiles = getEffectivePathsAndZipPaths(rootPath)

	for ep in effectivePaths:
		for dirpath,dirnames,filenames in os.walk(ep):
			folderpath = tmpPath + dirpath[len(rootPath):]
			if dirpath == ep:
				if not os.path.exists(folderpath):
					os.system('md ' + folderpath)

				for filename in filenames:
					if filename.find('.ogg') < 0 and filename.find('.zip') < 0:
						os.system('copy ' + os.path.join(dirpath,filename) + ' ' + folderpath)

				os.system(phpcommand.format(curPath() + '\\lib',folderpath,dirpath,ek,es))
				os.system('rd /q /s ' + folderpath)

	if not os.path.exists('md ' + tmpPath + slash + 'zip'):
		os.system('md ' + tmpPath + slash +'zip')

	for zp in zipFiles:
		srcpath = os.path.dirname(zp)
		zipfilename = os.path.basename(zp)
		folderarr = srcpath.split(slash)
		zippath = tmpPath + slash + 'zip' + slash + folderarr[len(folderarr)-1]
		tarpath = zippath

		z = zipfile.ZipFile(zp,'r')
		for zn in z.namelist():
			zn = zn.replace('/',slash)
			if not os.path.isdir(srcpath + slash + zn):
				if len(os.path.dirname(zn)) > 0:
					tarpath = zippath + slash + os.path.dirname(zn)

				if not os.path.exists(tarpath):
					os.system('md ' + tarpath)
				os.system('copy ' + srcpath + slash + zn + ' ' + tarpath)
				
		os.chdir(zippath)
		zipFolder('.', srcpath + slash + zipfilename)
		os.system('rd /s /q ' + zippath)
	os.system('rd /q /s ' + tmpPath)

if __name__ == '__main__':
	try:
		main()
	except Exception, e:
		print e