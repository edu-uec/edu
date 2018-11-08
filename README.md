# Edu

* Edu cpp version リポジトリ
[引用]
* julius-4.4.2.1
* dictation-kit-v4.4
を導入下で生成・実行している。

## 実行コマンド
edu.jconfのあるディレクトリで
`$ julius -C edu.jconf -nostrip -gram dict/ForAnnouncement`
と入力すると実行できる。
`ForAnnouncement`は辞書ファイル群で
`edu.jconf`は設定ファイルである。

edu.jconfの
```
-v model/lang_m/bccwj.60k.htkdic
-h model/phone_m/jnas-tri-3k16-gid.binhmm
-hlist model/phone_m/logicalTri
```
で指定されているmodelフォルダとその内部ファイルは、dictation-kit-v4.4のmodelフォルダのことである。

## juliusの受信修正
データの受信・抽出の機構を確立しました。修正方針は瓦解したXMLはそのままに、無理やりデータを抽出する感じで。
構造体order (juliusReceiver.hに記述あり) にデータを取り込みそのまま使える形にしてみました。参考はjuliusReceiver.cppをみてください。
