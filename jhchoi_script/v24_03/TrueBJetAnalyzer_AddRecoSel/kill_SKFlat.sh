ARR_PID=($(pgrep -f "python /data6/Users/jhchoi/SKFlatAnalyzers/test/ForTMVA/SKFlatAnalyzer/python/SKFlat.py"))

for pid in ${ARR_PID[@]};do
    kill ${pid}
done
