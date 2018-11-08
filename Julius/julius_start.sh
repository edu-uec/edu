kill $(lsof -ti:10500) #ポート10500で実行されているものをkillする
sleep 1 #1秒間スリープ
julius -C ../Julius/edu.jconf -nostrip -gram ../Julius/dict/TestAWord -module > /dev/null &
echo $! #プロセスIDを出力
sleep 2 #2秒間スリープ
