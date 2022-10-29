import sys
plat_path = 'D:\\CodeBase\\PycharmPrjs\\AoiOpt-Visual-Platform'
sys.path.append(plat_path)

from visual_plat.platform import VisualPlatform
from visual_plat.render_layer.layer_base import LayerBase
from visual_plat.global_proxy.color_proxy import ColorProxy
from visual_plat.shared.utility.anchor_tip import AnchorTip, AnchorLocate
from PySide6.QtGui import *
from PySide6.QtWidgets import *
from PySide6.QtCore import *
from dataclasses import dataclass
import pandas as pd

def toKB(size):
    return int(size / 1024)

def toMB(size):
    return size / 1024 / 1024

def toGB(size):
    return size / 1024 / 1024 / 1024

@dataclass
class MemMapUnit:
    type: int
    addr: str
    size: str
    start: int
    end : int
    size_i: int

class MapLayer(LayerBase):
    def __init__(self, canvas):
        super(MapLayer, self).__init__(canvas)
        self.mmp_list:list[MemMapUnit] = []
        self.tip_list:list[AnchorTip] = []
        self.show_tips = True

    def on_stage(self, device: QPixmap):
        tmp=[-20,-15,-10,-5,5,10,15,20]
        with QPainter(device) as painter:
            painter.setRenderHint(QPainter.Antialiasing)
            for i in range(len(self.tip_list)):
                loc=self.layout.crd2pos(QPoint(toMB(self.mmp_list[i].start)+tmp[i%8]+30, tmp[i%8]))
                self.tip_list[i].move(loc)
                painter.setPen(QPen(ColorProxy.idx_color(i,c_type="dark")))
                if self.show_tips:
                    painter.drawLine(self.layout.crd2pos(QPoint(toMB(self.mmp_list[i].start),0)),loc)
                    painter.drawLine(self.layout.crd2pos(QPoint(toMB(self.mmp_list[i].end),0)),loc)
        if self.show_tips:
            for tip in self.tip_list:
                tip.draw(device)
        return True
    
    def shift_state(self):
        self.show_tips = not self.show_tips
    
    def load_mmap(self, mmap_path):
        self.mmp_list.clear()
        self.tip_list.clear()
        df = pd.read_csv(mmap_path)
        for i in range(len(df)):
            map_unit = MemMapUnit(
                df['type'][i],
                df['addr'][i],
                df['size'][i],
                int(df['addr'][i], 16),
                int(df['addr'][i], 16) + int(df['size'][i], 16),
                int(df['size'][i], 16)
                )
            self.mmp_list.append(map_unit)
            tip = AnchorTip(AnchorLocate.top_lft)
            tip.set('type', map_unit.type)
            tip.set("start", map_unit.addr)
            tip.set("end", hex(map_unit.end))
            siz=str(toKB(map_unit.size_i))+"KB" if toKB(map_unit.size_i)<1024 else str(toMB(map_unit.size_i))+"MB"
            tip.set("size", str(map_unit.size)+f"({siz})")
            self.tip_list.append(tip)
        self.mmp_list.sort(key=lambda x: x.start)
        self.tip_list.sort(key=lambda x: x.get("start"))
        for i in range(len(self.tip_list)):
            self.tip_list[i].set("No",str(i))
        for i in range(len(self.mmp_list)):
            print(
                self.mmp_list[i].type,
                self.mmp_list[i].addr,
                self.mmp_list[i].size,
                toMB(self.mmp_list[i].start),
                toMB(self.mmp_list[i].end),
                toMB(self.mmp_list[i].size_i)
                )
        map_len = max([x.end for x in self.mmp_list])
        map = QPixmap(toMB(map_len), 100)
        with QPainter(map) as painter:
            for i in range(len(self.mmp_list)):
                painter.fillRect(
                    toMB(self.mmp_list[i].start),
                    0,
                    toMB(self.mmp_list[i].end),
                    100,
                    QBrush(ColorProxy.idx_color(i))
                )
        aoi_layer = self.canvas.get_layer('aoi')
        aoi_layer.agent.read_img(map.toImage())
        
        aoi_layer.reload_img()
        


map_layer_cfg = {
    "level": 3,
    "xps_tag": "MMP",
    "visible": True,
    "event": {
        "drop": {
            "csv": "load_mmap"
        },
        "key": {
            "shift+h": "shift_state"
        }
    }
}

canvas_config = VisualPlatform.mount_layer(MapLayer, "MMP", map_layer_cfg)

VisualPlatform.launch(plat_path=plat_path, canvas_config=canvas_config)
