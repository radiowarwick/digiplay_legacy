package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.Namespaces;
import org.dps.servicelayer.common.PermissionedItem;
import org.dps.servicelayer.dto.CartsetSummary;


@XmlAccessorType(XmlAccessType.PROPERTY)
public class PermissionedCartsetSummary extends PermissionedItem<CartsetSummary> {
    private CartsetSummary cartset;

    @XmlElement(required = true, namespace = Namespaces.DTO)
	public CartsetSummary getItem() {
		return cartset;
	}
	public void setItem(CartsetSummary cartset_) {
		cartset = cartset_;
	}
}
