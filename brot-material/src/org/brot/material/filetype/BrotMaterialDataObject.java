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
package org.brot.material.filetype;

import java.io.IOException;
import org.netbeans.core.spi.multiview.MultiViewElement;
import org.netbeans.core.spi.multiview.text.MultiViewEditorElement;
import org.openide.awt.ActionID;
import org.openide.awt.ActionReference;
import org.openide.awt.ActionReferences;
import org.openide.filesystems.FileObject;
import org.openide.filesystems.FileUtil;
import org.openide.filesystems.MIMEResolver;
import org.openide.loaders.DataObject;
import org.openide.loaders.DataObjectExistsException;
import org.openide.loaders.FileEntry;
import org.openide.loaders.MultiDataObject;
import org.openide.loaders.MultiFileLoader;
import org.openide.util.Lookup;
import org.openide.util.NbBundle.Messages;
import org.openide.windows.TopComponent;

@Messages({
    "LBL_BrotMaterial_LOADER=Files of BrotMaterial"
})
@MIMEResolver.NamespaceRegistration(
        displayName = "#LBL_BrotMaterial_LOADER",
        mimeType = "text/brot-material+xml",
        elementNS = {"org.brot.material"}
)
@DataObject.Registration(
        mimeType = "text/brot-material+xml",
        iconBase = "org/brot/material/filetype/icon.png",
        displayName = "#LBL_BrotMaterial_LOADER",
        position = 300
)
@ActionReferences({
    @ActionReference(
            path = "Loaders/text/brot-material+xml/Actions",
            id = @ActionID(category = "System", id = "org.openide.actions.OpenAction"),
            position = 100,
            separatorAfter = 200
    ),
    @ActionReference(
            path = "Loaders/text/brot-material+xml/Actions",
            id = @ActionID(category = "Edit", id = "org.openide.actions.CutAction"),
            position = 300
    ),
    @ActionReference(
            path = "Loaders/text/brot-material+xml/Actions",
            id = @ActionID(category = "Edit", id = "org.openide.actions.CopyAction"),
            position = 400,
            separatorAfter = 500
    ),
    @ActionReference(
            path = "Loaders/text/brot-material+xml/Actions",
            id = @ActionID(category = "Edit", id = "org.openide.actions.DeleteAction"),
            position = 600
    ),
    @ActionReference(
            path = "Loaders/text/brot-material+xml/Actions",
            id = @ActionID(category = "System", id = "org.openide.actions.RenameAction"),
            position = 700,
            separatorAfter = 800
    ),
    @ActionReference(
            path = "Loaders/text/brot-material+xml/Actions",
            id = @ActionID(category = "System", id = "org.openide.actions.SaveAsTemplateAction"),
            position = 900,
            separatorAfter = 1000
    ),
    @ActionReference(
            path = "Loaders/text/brot-material+xml/Actions",
            id = @ActionID(category = "System", id = "org.openide.actions.FileSystemAction"),
            position = 1100,
            separatorAfter = 1200
    ),
    @ActionReference(
            path = "Loaders/text/brot-material+xml/Actions",
            id = @ActionID(category = "System", id = "org.openide.actions.ToolsAction"),
            position = 1300
    ),
    @ActionReference(
            path = "Loaders/text/brot-material+xml/Actions",
            id = @ActionID(category = "System", id = "org.openide.actions.PropertiesAction"),
            position = 1400
    )
})
public class BrotMaterialDataObject extends MultiDataObject {

    private static final MultiFileLoader FORCED_LOADER = new MultiFileLoader(BrotMaterialDataObject.class) {

        @Override
        protected FileObject findPrimaryFile(FileObject fo) {
            return "xml".equals(fo.getExt()) ? fo : FileUtil.findBrother(fo, "xml");
        }

        @Override
        protected MultiDataObject createMultiObject(FileObject primaryFile) throws DataObjectExistsException, IOException {
            return new BrotMaterialDataObject(primaryFile, this);
        }

        @Override
        protected Entry createPrimaryEntry(MultiDataObject obj, FileObject primaryFile) {
            return new FileEntry(obj, primaryFile);
        }

        @Override
        protected Entry createSecondaryEntry(MultiDataObject obj, FileObject secondaryFile) {
            return new FileEntry(obj, secondaryFile);
        }
    };

    public BrotMaterialDataObject(FileObject pf, MultiFileLoader loader) throws DataObjectExistsException, IOException {
        // The annotation processor uses MimeFactory to create instances. That
        // one uses a canned instance from DataLoaderPool, which does not
        // support secondary files. If we register the MFL itself, then we don't
        // get the node for free, so we would need a BrotMaterialNode as well.
        super(pf, FORCED_LOADER);
        registerEditor("text/brot-material+xml", true);
        // registerEntry(FileUtil.findBrother(pf, "..."));
    }

    @Override
    protected int associateLookup() {
        return 1;
    }

    @MultiViewElement.Registration(
            displayName = "#LBL_BrotMaterial_EDITOR",
            iconBase = "org/brot/material/filetype/icon.png",
            mimeType = "text/brot-material+xml",
            persistenceType = TopComponent.PERSISTENCE_ONLY_OPENED,
            preferredID = "BrotMaterial",
            position = 1000
    )
    @Messages("LBL_BrotMaterial_EDITOR=Source")
    public static MultiViewEditorElement createEditor(Lookup lkp) {
        return new MultiViewEditorElement(lkp);
    }

}
