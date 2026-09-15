for i in {1..300}; do
    echo $i
    kill -9 %"${i}"
done
