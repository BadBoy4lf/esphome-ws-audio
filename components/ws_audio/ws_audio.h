#pragma once
#include "esphome.h"
#include "esphome/components/websocket_client/websocket_client.h"

class WebSocketAudio : public esphome::Component {
 public:
  void setup() override {
    client_ = new esphome::websocket_client::WebSocketClient();
    client_->set_url("ws://192.168.177.1:1880/endpoint/audio");
    client_->set_reconnect(true);
    ESP_LOGI("ws_audio", "WebSocketAudio setup completed");
  }

  void start_stream() {
    if (!client_) return;
    ESP_LOGI("ws_audio", "Starting WebSocket stream…");
    client_->connect();
    active_ = true;
  }

  void stop_stream() {
    if (!client_) return;
    ESP_LOGI("ws_audio", "Stopping WebSocket stream…");
    client_->close();
    active_ = false;
  }

  void send_chunk(const uint8_t *data, size_t len) {
    if (!active_ || !client_) return;
    client_->send_binary(data, len);
  }

  bool is_active() const { return active_; }

 private:
  esphome::websocket_client::WebSocketClient *client_{nullptr};
  bool active_{false};
};
