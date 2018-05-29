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
package org.brot.xml;

import java.util.Set;
import javax.annotation.processing.Processor;
import javax.annotation.processing.RoundEnvironment;
import javax.annotation.processing.SupportedAnnotationTypes;
import javax.annotation.processing.SupportedSourceVersion;
import javax.lang.model.SourceVersion;
import javax.lang.model.element.Element;
import javax.lang.model.element.TypeElement;
import org.brot.xml.spi.DOMLookupProvider;
import org.openide.filesystems.annotations.LayerGeneratingProcessor;
import org.openide.filesystems.annotations.LayerGenerationException;
import org.openide.util.lookup.ServiceProvider;

/**
 * Somewhat based on org.netbeans.modules.projectapi.LookupProviderAnnotationProcessor.
 */
@ServiceProvider(service = Processor.class)
@SupportedSourceVersion(SourceVersion.RELEASE_7)
@SupportedAnnotationTypes("org.brot.xml.spi.DOMLookupProvider.Registration")
public class LookupProviderAnnotationProcessor extends LayerGeneratingProcessor {

    @Override
    protected boolean handleProcess(Set<? extends TypeElement> annotations, RoundEnvironment roundEnv) throws LayerGenerationException {
        if (roundEnv.processingOver()) {
            return false;
        }
        for (Element e : roundEnv.getElementsAnnotatedWith(DOMLookupProvider.Registration.class)) {
            DOMLookupProvider.Registration lpr = e.getAnnotation(DOMLookupProvider.Registration.class);
            if (lpr.mimeType().length == 0) {
                throw new LayerGenerationException("You must specify at least one file type", e, processingEnv, lpr);
            }
            for (String type : lpr.mimeType()) {
                layer(e).instanceFile("Loaders/" + type + "/Lookups", null, DOMLookupProvider.class, lpr, null).write();
            }
        }
        return true;
    }

}
