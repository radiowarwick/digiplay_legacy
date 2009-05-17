package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.Namespaces;
import org.dps.servicelayer.common.PermissionedItem;
import org.dps.servicelayer.dto.Cartset;


@XmlAccessorType(XmlAccessType.NONE)
public class PermissionedCartset extends PermissionedItem<Cartset> {
    private Cartset cartset;

    @XmlElement(required = true, namespace = Namespaces.DTO)
	public Cartset getItem() {
		return cartset;
	}
	public void setItem(Cartset cartset_) {
		cartset = cartset_;
	}
}
