## 리눅스 파일 개수 및 디렉토리 개수 세기


- 현재 위치에서 폴더 개수 세기
>  ls -l | grep ^d | wc -l

- 현재 위치에서 파일의 개수 세기
> ls -l | grep ^- | wc -l

- 현재 디렉토리의 하위 파일 개수 세기
> find . -type f | wc -l


## linux  파일 옮기기

- 
> ls -1 | head -10 | xargs -i mv "{}" /{file_path}

## move file that include specific string in the filename
> mv $(find path_A -name "*AAA*") path_B

## file zip
> zip -r $zip_file_name.zip $/path/to/curr/dir

## delete all files
> 

## rename filename
> for file in F*png; do new_file=$(cut -c3- <<< "$file"); mv "$file" "$new_file"; done


## find size n(natural number)
> find . -size n

> -------------------------------------------
# partition

## set write mode to new partition
> sudo chown yourusername .

> sudo chmod 777

## change mounting point of linux partition
> cat /etc/fstab

> mount -v

> fuser -mv /media/john/14~~

> mkdir /home/john/DLstorage

> umount /media/john/14~~

> mount /dev/sdc1 /home/john/DLstorage

> df


## NVIDIA Driver Installation
> sudo lspci -vnn |grep VGA

> sudo dpkg --add-architecture i386

> sudo apt update

> sudo apt install build-essential libc6:i386

#### If Error occurs
#### E: could not get lock /var/lib/dpkg/lock-frontend.

  > sudo killall apt apt-get
  
  > sudo rm /var/lib/apt/lists/lock

  > sudo rm /var/cache/apt/archives/lock

  > sudo rm /var/lib/dpkg/lock*
  
  > sudo dpkg --configure -a

  > sudo apt update
