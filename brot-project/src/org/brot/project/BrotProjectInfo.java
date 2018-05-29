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
import java.beans.PropertyChangeListener;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import org.brot.project.api.BrotProject;
import org.netbeans.api.project.Project;
import org.netbeans.api.project.ProjectInformation;
import org.netbeans.spi.project.ProjectServiceProvider;
import org.openide.util.ImageUtilities;

/**
 *
 * @author m4c0@users.noreply.github.com
 */
@ProjectServiceProvider(service = ProjectInformation.class, projectType = BrotProject.PROJECT_ID)
public class BrotProjectInfo implements ProjectInformation {

    public static final String ICON = "org/brot/project/icon.png";
    
    private final Project project;

    public BrotProjectInfo(Project project) {
        this.project = project;
    }
    
    @Override
    public String getName() {
        return project.getProjectDirectory().getName();
    }

    @Override
    public String getDisplayName() {
        return getName();
    }

    @Override
    public Icon getIcon() {
        return new ImageIcon(getAwtImage());
    }
    
    public Image getAwtImage() {
        return ImageUtilities.loadImage(ICON);
    }

    @Override
    public Project getProject() {
        return project;
    }

    @Override
    public void addPropertyChangeListener(PropertyChangeListener listener) {
    }

    @Override
    public void removePropertyChangeListener(PropertyChangeListener listener) {
    }

}
