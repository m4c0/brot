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
package org.brot.material.parser;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.brot.material.api.BrotMaterial;
import org.openide.filesystems.FileObject;
import org.openide.nodes.CookieSet;
import org.openide.nodes.Node;
import org.openide.util.Exceptions;
import org.openide.xml.XMLUtil;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class BrotMaterialParser implements CookieSet.Factory {

    private final FileObject file;

    public BrotMaterialParser(FileObject pf) {
        file = pf;
    }

    @Override
    public <T extends Node.Cookie> T createCookie(Class<T> klass) {
        try {
            return tryCreateCookie(klass);
        } catch (Exception ex) {
            Exceptions.printStackTrace(ex);
            return null;
        }
    }

    private <T extends Node.Cookie> T tryCreateCookie(Class<T> klass) throws Exception {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        builder.setErrorHandler(XMLUtil.defaultErrorHandler());

        Document doc = builder.parse(file.getInputStream());
        Element root = doc.getDocumentElement();

        Element schema = XMLUtil.findElement(root, "schema", null);

        BrotMaterial result = new BrotMaterial();

        return klass.cast(result);
    }

}
