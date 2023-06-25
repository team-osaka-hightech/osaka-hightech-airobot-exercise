# osaka-hightech-airobot-exercise
電気電子回路実習Ⅱで制作するロボットに関するリポジトリです。

--

セットアップ用のスクリプトを実行する場合は、まず以下のコマンドでスクリプトファイル(Raw)をダウンロードします。
```
$ wget "https://raw.githubusercontent.com/team-osaka-hightech/osaka-hightech-airobot-exercise/main/setup.sh"
```

`ls`コマンドを使うと、カレントディレクトリ（現在いるディレクトリ）に`setup.sh`というファイルが追加されていることが分かります。
ここで、
```
$ sh setup.sh
```
コマンドを実行すると、セットアップが進行します。途中、**[Y]/n ?** と表示されたらEnterキーを押して進めてください。  
※ **Error** や **E:** が表示される場合は何らかのトラブルが発生しています

ネットワークやSDカードの性能によって所要時間は異なりますが、だいたい10分ほど完了します。

--

セットアップが完了したら、実際に物体認識デモを試してみます。  
VNCビューワーなどでRaspberryPiのデスクトップを開いてください。合わせて、デスクトップ上でターミナルを起動します。  
デモ用のpythonスクリプトを起動するスクリプトファイル(Raw)をダウンロードします。
```
$ wget "https://raw.githubusercontent.com/team-osaka-hightech/osaka-hightech-airobot-exercise/main/object_detect.sh"
```

RaspberryPiにUSBカメラ等を接続します。  
ここで、
```
$ sh object_detech.sh
```
コマンドを実行すると、カメラ映像が表示され、リアルタイムで物体認識が行われます。

