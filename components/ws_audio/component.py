import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

ws_audio_ns = cg.esphome_ns.namespace("ws_audio")
WebSocketAudio = ws_audio_ns.class_("WebSocketAudio", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(WebSocketAudio),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
