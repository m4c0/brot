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
package org.brot.material.scene;

import org.brot.material.spi.BrotMaterialSceneNode;
import org.netbeans.api.visual.graph.GraphScene;
import org.netbeans.api.visual.widget.LayerWidget;
import org.netbeans.api.visual.widget.Widget;
import org.openide.util.Lookup;

public class MaterialScene<Edge> extends GraphScene<BrotMaterialSceneNode, Edge> {

    private final Lookup.Result<BrotMaterialSceneNode> nodeLookupResult;

    private final LayerWidget mainLayer = new LayerWidget(this);

    public MaterialScene(Lookup dataObjLookup) {
        // TODO: listen to changes
        nodeLookupResult = dataObjLookup.lookupResult(BrotMaterialSceneNode.class);
        for (BrotMaterialSceneNode node : nodeLookupResult.allInstances()) {
            addNode(node);
        }

        addChild(mainLayer);
    }

    @Override
    protected Widget attachNodeWidget(BrotMaterialSceneNode node) {
        Widget w = node.createWidget(this);
        mainLayer.addChild(w);
        return w;
    }

    @Override
    protected Widget attachEdgeWidget(Edge edge) {
        return null;
    }

    @Override
    protected void attachEdgeSourceAnchor(Edge edge, BrotMaterialSceneNode oldSourceNode, BrotMaterialSceneNode sourceNode) {
    }

    @Override
    protected void attachEdgeTargetAnchor(Edge edge, BrotMaterialSceneNode oldTargetNode, BrotMaterialSceneNode targetNode) {
    }

}
