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
package org.brot.xml.api;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import org.brot.xml.spi.DOMLookupProvider;
import org.openide.filesystems.FileObject;
import org.openide.loaders.DataObjectExistsException;
import org.openide.loaders.MultiDataObject;
import org.openide.loaders.MultiFileLoader;
import org.openide.util.Lookup;
import org.openide.util.lookup.Lookups;
import org.openide.util.lookup.ProxyLookup;

public abstract class DOMDataObject extends MultiDataObject {

    private Lookup lkp;

    public DOMDataObject(FileObject pf, MultiFileLoader loader) throws DataObjectExistsException, IOException {
        super(pf, loader);

        getCookieSet().assign(DOMProvider.class, new DOMProvider(pf));
    }

    @Override
    public Lookup getLookup() {
        if (lkp == null) {
            lkp = new LookupMerger(super.getLookup(), "Loaders/" + getPrimaryFile().getMIMEType() + "/Lookups");
        }
        return lkp;
    }

    private class LookupMerger extends ProxyLookup {

        LookupMerger(Lookup base, String lookupPath) {
            // TODO: Listen for changes
            // TODO: Copy other behaviours from LookupProviderSupport (such as checking if folder only contains valid classes)
            List<Lookup> all = new ArrayList<>();
            all.add(base);

            for (DOMLookupProvider dlp : Lookups.forPath(lookupPath).lookupAll(DOMLookupProvider.class)) {
                all.add(dlp.createAdditionalLookup(base));
            }

            setLookups(all.toArray(new Lookup[all.size()]));
        }
    }

}
