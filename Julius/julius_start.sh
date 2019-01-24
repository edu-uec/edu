PID=`lsof -ti:10500`
echo $PID
if [ -z "$PID"]; then
       	echo "pid is unset"
else 
	kill $PID #ポート10500で実行されているものをkillする
fi


sleep 1 #1秒間スリープ
julius -C ../Julius/edu.jconf -nostrip -gram ../Julius/dict/TestAWord -module > /dev/null &
echo $! #プロセスIDを出力
sleep 2 #2秒間スリープ
