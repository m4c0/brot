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
package org.brot.project.api;

import org.netbeans.api.project.Project;
import org.netbeans.spi.project.support.LookupProviderSupport;
import org.openide.filesystems.FileObject;
import org.openide.util.Lookup;
import org.openide.util.lookup.Lookups;

/**
 *
 * @author m4c0@users.noreply.github.com
 */
public final class BrotProject implements Project {

    public static final String PROJECT_ID = "org-brot-project";

    private final FileObject directory;
    private Lookup lkp;

    public BrotProject(FileObject directory) {
        this.directory = directory;
    }
    
    @Override
    public FileObject getProjectDirectory() {
        return directory;
    }

    @Override
    public Lookup getLookup() {
        if (lkp == null) {
            lkp = LookupProviderSupport.createCompositeLookup(Lookups.fixed(this), "Projects/" + PROJECT_ID + "/Lookup");
        }
        return lkp;
    }

}
