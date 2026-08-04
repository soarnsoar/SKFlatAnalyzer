ARR_F=$(cat print_files_with_emptybin.txt)
echo "RM following files"
for F in ${ARR_F[@]};do
    echo $F
    rm $F
done
