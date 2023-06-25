# osaka-hightech-airobot-exercise
電気電子回路実習Ⅱで制作するロボットに関するリポジトリです。

--

セットアップ用のスクリプトを実行する場合は、まず以下のコマンドでスクリプトファイル(Raw)をダウンロードします。
###### 『$』はすでに表示されているので入力の必要ありません。説明内でコマンドであることを示します
```
$ wget "https://raw.githubusercontent.com/team-osaka-hightech/osaka-hightech-airobot-exercise/main/setup.sh"
```

`ls`コマンドを使うと、カレントディレクトリ（現在いるディレクトリ）に`setup.sh`というファイルが追加されていることが分かります。
ここで、
```
$ sh setup.sh
```
コマンドを実行すると、セットアップが進行します。途中、**[Y/n] ?** と表示されたらEnterキーを押して進めてください。  
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


## detect.pyを改造して使う
先ほどのデモは、リアルタイム物体認識を画面上で確認するだけでした。次は、認識した結果を用いて色々活用してみましょう。  
まずはdetect.pyの置いてあるディレクトリに移動します。
`/examples/lite/examples/object_detection/raspberry_pi`

ここに置いてある`detect.py`をテキストエディタ等で開き、このリポジトリに置いてある`detect.py`の内容と置き換えます。  
置き換えたファイルは、人間(person)を検出したら、その中心座標(x,y)を表示しつつ、GPIOのpin26をON/OFFします。LEDを接続して確認してください。  

これを使って次のアイデアを実現しましょう。  
- 人を検出したらGPIOで2つのモーターを制御し、人のいる方向へ進むロボットを作る
