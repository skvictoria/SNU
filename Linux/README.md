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
