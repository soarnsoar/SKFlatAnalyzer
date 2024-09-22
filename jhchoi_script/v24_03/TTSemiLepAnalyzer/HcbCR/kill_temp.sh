for i in {25..72}; do
    echo $i
    kill %"${i}"
done
