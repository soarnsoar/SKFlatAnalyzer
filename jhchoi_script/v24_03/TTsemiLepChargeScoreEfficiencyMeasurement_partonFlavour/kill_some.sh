#57
for i in {57..100}; do
    echo $i
    kill %"${i}"
done
