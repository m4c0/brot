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

package org.brot.material.spi;

import org.netbeans.api.visual.widget.Scene;
import org.netbeans.api.visual.widget.Widget;

public interface BrotMaterialSceneNode {

    Widget createWidget(Scene scene);

}
