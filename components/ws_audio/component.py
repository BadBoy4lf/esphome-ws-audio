import esphome.codegen as cg

ws_audio_ns = cg.esphome_ns.namespace("ws_audio")
WebSocketAudio = ws_audio_ns.class_("WebSocketAudio", cg.Component)
