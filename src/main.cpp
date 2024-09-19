#include <M5Unified.h>
#include <Avatar.h>

using namespace m5avatar;
Avatar avatar;
ColorPalette *cp;

char speechText[100];  // フォーマットされた文字列を格納するためのバッファ
bool isNatural = true;
bool isBeer = true;

hw_timer_t * timer = NULL;  // タイマー設定

void onTimer(){
  if (isBeer) {
    if (isNatural) {
      avatar.setExpression(m5avatar::Expression::Neutral);
      avatar.setSpeechText("");
      isNatural = false;
    } else {
      avatar.setExpression(m5avatar::Expression::Happy);
      sprintf(speechText, "I LV Beer!!");
      avatar.setSpeechText(speechText);
      isNatural = true;
    }
  }
}

void setup() {
  auto cfg = M5.config();     // 設定用の情報を抽出
  cfg.output_power = true;   // Groveポートの出力をしない
  M5.begin(cfg);              // M5Stackをcfgの設定で初期化

  // 顔ポジション設定（m5atomS3用）
  M5.Lcd.setRotation(0);
  avatar.setScale(0.50);
  avatar.setPosition(-58, -96);

  // アバター初期設定
  cp = new ColorPalette();
  cp->set(COLOR_PRIMARY, TFT_WHITE);
  cp->set(COLOR_BACKGROUND, TFT_ORANGE);
  avatar.setColorPalette(*cp);
  avatar.setSpeechFont(&fonts::lgfxJapanGothicP_16);
  avatar.init(8);
  avatar.setExpression(m5avatar::Expression::Happy);
  sprintf(speechText, "I LV Beer!!");
  avatar.setSpeechText(speechText);

  // タイマー設定
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 5000000, true);
  timerAlarmEnable(timer);

}

void loop() {

  M5.update();

  if (M5.BtnA.wasClicked())
  {
    if (isBeer) {
      cp->set(COLOR_PRIMARY, TFT_BLACK);
      cp->set(COLOR_BACKGROUND, TFT_WHITE);
      avatar.setColorPalette(*cp);
      avatar.setExpression(m5avatar::Expression::Neutral);
      sprintf(speechText, "No Beer!!");
      avatar.setSpeechText(speechText);
      isBeer = false;
    } else {
      cp->set(COLOR_PRIMARY, TFT_WHITE);
      cp->set(COLOR_BACKGROUND, TFT_ORANGE);
      avatar.setColorPalette(*cp);
      avatar.setExpression(m5avatar::Expression::Happy);
      sprintf(speechText, "More Beer!!");
      avatar.setSpeechText(speechText);
      isBeer = true;
    }
  }

  delay(1);
}
