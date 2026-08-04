for i in {2..100}; do
    echo $i
    kill %"${i}"
done
