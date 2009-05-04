package org.dps.servicelayer.cartset.wrappers;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.common.PermissionedItem;
import org.dps.servicelayer.dto.Cartset;


@XmlAccessorType(XmlAccessType.PROPERTY)
public class PermissionedCartset extends PermissionedItem {
    private Cartset cartset;

    @XmlElement(required = true)
	public Cartset getCartset() {
		return cartset;
	}
	public void setCartset(Cartset cartset_) {
		cartset = cartset_;
	}
}
