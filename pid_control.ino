// PID制御実習プログラム
boolean serial_mode = 0; // シリアルモニタに表示する情報（0:全て, 1:目標・現在の値・制御量）
double target = 300.0; // 起動時の目標値 ※設定範囲は300~700とすること
double current; // 現在の値（出力）

double kp = 0; // 比例ゲイン
double ki = 0; // 積分ゲイン
double kd = 0; // 微分ゲイン

double control_value = 0; // 制御量
double deviation = 0; // 目標と現在の値との偏差
double integral_addition = 0; // 偏差の過去の積算（積分）
double derivative_prev = 0; // 偏差の変化率（微分）計算用 直前データの保管

void IntrChangeTargetValue(void); // 割り込み関数の定義

void setup() {
  attachInterrupt(0, IntrChangeTargetValue, FALLING);
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(10, OUTPUT); //for CW
  pinMode(11, OUTPUT); //for CCW
  Serial.println();
  if (serial_mode)
    Serial.println("target, current, Control_Value");
  else
    Serial.println("target, current, Control_Value, deviation, integral_add, derivative");
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  delay(1000);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void loop() {
  readCurrentPosition(); // 現在の値（出力・角度）を読み取る
  derivative_prev = deviation;  // 直前のデータを保持
  deviation = target - current; // 偏差の計算
  integral_addition += (deviation / 1000); // 偏差の積算（1/1000に調整）

  control_value = deviation * kp + integral_addition * ki + (deviation - derivative_prev) * kd; // 制御量の計算
  control_value = constrain(control_value, -255, 255); // 制御量をArduinoの限界値(255)に制限

  if (target < current) // 目標値より小さいとき正転
    SetCW(-control_value);
  else if (target > current) // 目標値より大きいとき逆転
    SetCCW(control_value);
  serialPrintInfo(serial_mode); // シリアルモニタに情報を表示
}


// 自作関数群 ////////////////////////////////////////////////////////////

double readCurrentPosition() {
  current = target; //初期化
  for (int i = 0; i < 10; i++) // 現在の角度情報を更新（10回平均）
    current += analogRead(A1);
  current /= 10;
  current = round(current);
}

void IntrChangeTargetValue() { // D2のスイッチで割り込み処理
  digitalWrite(13, HIGH);
  integral_addition = 0;
  kp=0.1;ki=1;kd=0;
  target = 300;
}

void SetCW(int value) { // 正転
  digitalWrite(10, LOW);
  analogWrite(11, constrain(value, 0, 255));
}

void SetCCW(int value) { // 逆転
  analogWrite(10, constrain(value, 0, 255));
  digitalWrite(11, LOW);
}

void SetStop() { // 停止
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void serialEvent() { // シリアル通信で数値（3桁以内）を受け取るとtargetに格納する（100~999）
  String serial_received_value = Serial.readStringUntil('\n');
  int string_len = serial_received_value.length();
  if ((string_len >= 1) && (string_len <= 3))// 指定文字数内のとき文字列を整数に変換する
    target = serial_received_value.toInt();
  deviation = 0;
  integral_addition = 0;
  derivative_prev = 0;
}

void serialPrintInfo(boolean mode) {
  if (mode) {
    Serial.print(target);
    Serial.print(",");
    Serial.print(current);
    Serial.print(",");
    Serial.println(control_value);
  }
  else {
    Serial.print(target);
    Serial.print(",");
    Serial.print(current);
    Serial.print(",");
    Serial.print(control_value);
    Serial.print(",");
    Serial.print(deviation);
    Serial.print(",");
    Serial.print(integral_addition);
    Serial.print(",");
    Serial.println(deviation - derivative_prev);
  }
}

