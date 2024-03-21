for i in {1..100}; do
    echo $i
    kill %"${i}"
done
