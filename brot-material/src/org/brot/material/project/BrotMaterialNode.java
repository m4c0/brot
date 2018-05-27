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
package org.brot.material.project;

import java.awt.Image;
import javax.swing.Action;
import org.brot.material.filetype.BrotMaterialDataObject;
import org.brot.project.spi.BrotProject;
import org.netbeans.api.project.Project;
import org.netbeans.spi.project.ui.support.NodeFactory;
import org.netbeans.spi.project.ui.support.NodeFactorySupport;
import org.netbeans.spi.project.ui.support.NodeList;
import org.openide.filesystems.FileObject;
import org.openide.loaders.DataObject;
import org.openide.loaders.DataObjectNotFoundException;
import org.openide.nodes.FilterNode;
import org.openide.nodes.Node;
import org.openide.util.Exceptions;
import org.openide.util.ImageUtilities;
import org.openide.util.NbBundle;

/**
 *
 * @author m4c0@users.noreply.github.com
 */
@NodeFactory.Registration(projectType = BrotProject.PROJECT_ID, position = 100)
public class BrotMaterialNode implements NodeFactory {

    private static final String ICON = "org/brot/material/project/icon.png";

    @Override
    public NodeList<?> createNodes(Project p) {
        try {
            Node node = DataObject.find(p.getProjectDirectory()).getNodeDelegate();
            return NodeFactorySupport.fixedNodeList(new MaterialNode(p, node));
        } catch (DataObjectNotFoundException ex) {
            Exceptions.printStackTrace(ex);
            return NodeFactorySupport.fixedNodeList();
        }
    }

    private static class MaterialNode extends FilterNode {

        public MaterialNode(Project p, Node node) throws DataObjectNotFoundException {
            super(node, new MaterialChildren(node));
        }

        @Override
        public Action[] getActions(boolean context) {
            return new Action[] {
            };
        }

        @Override
        public Image getIcon(int type) {
            return ImageUtilities.loadImage(ICON);
        }

        @Override
        public Image getOpenedIcon(int type) {
            return getIcon(type);
        }

        @Override
        public String getName() {
            return super.getName() + "-materials";
        }

        @Override
        public String getDisplayName() {
            return NbBundle.getMessage(BrotMaterialNode.class, "LBL_ProjectMaterialNode");
        }

    }

    private static class MaterialChildren extends FilterNode.Children {

        public MaterialChildren(Node or) {
            super(or);
        }

        @Override
        protected Node[] createNodes(Node key) {
            String mimeType = key.getLookup().lookup(FileObject.class).getMIMEType();
            if (!BrotMaterialDataObject.MIME_TYPE.equals(mimeType)) {
                return new Node[0];
            }
            return new Node[] { key.cloneNode() };
        }
    }

}
