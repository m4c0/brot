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
package org.brot.project;

import java.awt.Image;
import javax.swing.Action;
import javax.swing.ImageIcon;
import org.brot.project.api.BrotProject;
import org.netbeans.api.project.Project;
import org.netbeans.api.project.ProjectUtils;
import org.netbeans.spi.project.ui.support.CommonProjectActions;
import org.netbeans.spi.project.ui.support.NodeFactorySupport;
import org.openide.nodes.FilterNode;
import org.openide.nodes.Node;
import org.openide.util.lookup.Lookups;
import org.openide.util.lookup.ProxyLookup;

/**
 *
 * @author m4c0@users.noreply.github.com
 */
class BrotProjectNode extends FilterNode {

    private final Project project;

    public BrotProjectNode(Project project, Node node) {
        super(node,
                NodeFactorySupport.createCompositeChildren(project, "Projects/" + BrotProject.PROJECT_ID + "/Nodes"),
                new ProxyLookup(Lookups.singleton(project), node.getLookup()));
        
        this.project = project;
    }
    
    @Override
    public Action[] getActions(boolean context) {
        return new Action[]{
            CommonProjectActions.copyProjectAction(),
            CommonProjectActions.moveProjectAction(),
            CommonProjectActions.deleteProjectAction(),
            CommonProjectActions.closeProjectAction()
        };
    }

    @Override
    public Image getIcon(int type) {
        return ((ImageIcon) ProjectUtils.getInformation(project).getIcon()).getImage();
    }

    @Override
    public Image getOpenedIcon(int type) {
        return getIcon(type);
    }

    @Override
    public String getDisplayName() {
        return ProjectUtils.getInformation(project).getDisplayName();
    }
}
