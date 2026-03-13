#pragma once
#include "esphome.h"
#include <esp_websocket_client.h>

class WebSocketAudio : public esphome::Component {
 public:
  void setup() override {
    esp_websocket_client_config_t cfg = {};
    cfg.uri = "ws://192.168.177.1:1880/endpoint/audio";
    client_ = esp_websocket_client_init(&cfg);
  }

  void start_stream() {
    if (!client_) return;
    ESP_LOGI("ws_audio", "Starting WebSocket stream…");
    esp_websocket_client_start(client_);
    active_ = true;
  }

  void stop_stream() {
    if (!client_) return;
    ESP_LOGI("ws_audio", "Stopping WebSocket stream…");
    esp_websocket_client_stop(client_);
    active_ = false;
  }

  void send_chunk(const uint8_t *data, size_t len) {
    if (!active_ || !client_) return;
    esp_websocket_client_send_bin(client_, (const char *)data, len, portMAX_DELAY);
  }

  bool is_active() const { return active_; }

 private:
  esp_websocket_client_handle_t client_{nullptr};
  bool active_{false};
};