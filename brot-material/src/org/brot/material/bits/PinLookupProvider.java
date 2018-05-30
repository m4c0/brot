/*
    Brot - An IDE for designing PCBs
    Copyright (C) 2018 - Eduardo Costa

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
package org.brot.material.bits;

import java.awt.BasicStroke;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Rectangle;
import java.io.IOException;
import java.util.List;
import org.brot.material.filetype.BrotMaterialDataObject;
import org.brot.material.spi.BrotMaterialSceneNode;
import org.brot.xml.api.DOMProvider;
import org.brot.xml.spi.DOMLookupProvider;
import org.netbeans.api.visual.action.ActionFactory;
import org.netbeans.api.visual.action.MoveStrategy;
import org.netbeans.api.visual.widget.Scene;
import org.netbeans.api.visual.widget.Widget;
import org.openide.util.Exceptions;
import org.openide.util.Lookup;
import org.openide.util.lookup.InstanceContent;
import org.openide.util.lookup.Lookups;
import org.openide.xml.XMLUtil;
import org.w3c.dom.Element;

/**
 *
 * @author m4c0@users.noreply.github.com
 */
@DOMLookupProvider.Registration(mimeType = BrotMaterialDataObject.MIME_TYPE)
public class PinLookupProvider implements DOMLookupProvider {

    @Override
    public Lookup createAdditionalLookup(Lookup baseContext) {
        try {
            // TODO: lazy load this, only when requested
            return tryToCreateAdditionalLookup(baseContext);
        } catch (IOException ex) {
            Exceptions.printStackTrace(ex);
            return Lookup.EMPTY;
        }
    }

    private Lookup tryToCreateAdditionalLookup(Lookup baseContext) throws IOException {
        Element root = baseContext.lookup(DOMProvider.class).getRootElement();
        Element pins = XMLUtil.findElement(root, "pins", null);
        if (pins == null) return Lookup.EMPTY;

        List<Element> pinList = XMLUtil.findSubElements(pins);
        Element[] pinArray = pinList.toArray(new Element[pinList.size()]);
        return Lookups.fixed(pinArray, new InstanceContent.Convertor<Element, Pin>() {

            @Override
            public Pin convert(Element obj) {
                return new Pin(obj.getAttribute("id"));
            }

            @Override
            public Class<? extends Pin> type(Element obj) {
                return Pin.class;
            }

            @Override
            public String id(Element obj) {
                return obj.getAttribute("id");
            }

            @Override
            public String displayName(Element obj) {
                return obj.getAttribute("name");
            }

        });
    }

    private static class Pin implements BrotMaterialSceneNode {

        private final String id;

        public Pin(String id) {
            this.id = id;
        }

        @Override
        public Widget createWidget(Scene s) {
            Widget w = new PinWidget(s);
            w.getActions().addAction(ActionFactory.createMoveAction(new MoveStrategy() {
                @Override
                public Point locationSuggested(Widget widget, Point originalLocation, Point suggestedLocation) {
                    Point res = new Point();
                    res.x = suggestedLocation.x - suggestedLocation.x % 5;
                    res.y = suggestedLocation.y - suggestedLocation.y % 5;
                    return res;
                }
            }, null));
            return w;
        }

    }

    private static class PinWidget extends Widget {

        public PinWidget(Scene scene) {
            super(scene);
        }

        @Override
        protected Rectangle calculateClientArea() {
            return new Rectangle(0, 0, 10, 10);
        }

        @Override
        protected void paintWidget() {
            Graphics2D g = getGraphics();
            g.setColor(getForeground());
            g.setStroke(new BasicStroke(2));
            g.drawOval(0, 0, 5, 5);
        }
    }

}
