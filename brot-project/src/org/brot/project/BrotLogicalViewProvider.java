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

import org.brot.project.api.BrotProject;
import org.netbeans.api.project.Project;
import org.netbeans.spi.project.ProjectServiceProvider;
import org.netbeans.spi.project.ui.LogicalViewProvider;
import org.openide.filesystems.FileObject;
import org.openide.loaders.DataFolder;
import org.openide.nodes.Node;

/**
 *
 * @author m4c0@users.noreply.github.com
 */
@ProjectServiceProvider(service = LogicalViewProvider.class, projectType = BrotProject.PROJECT_ID)
public class BrotLogicalViewProvider implements LogicalViewProvider {

    private final Project project;

    public BrotLogicalViewProvider(Project project) {
        this.project = project;
    }

    @Override
    public Node createLogicalView() {
        FileObject dir = project.getProjectDirectory();
        DataFolder dataFolder = DataFolder.findFolder(dir);
        return new BrotProjectNode(project, dataFolder.getNodeDelegate());
    }

    @Override
    public Node findPath(Node root, Object target) {
        return null;
    }
}
