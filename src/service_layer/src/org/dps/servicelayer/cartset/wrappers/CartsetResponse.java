package org.dps.servicelayer.cartset.wrappers;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.PROPERTY)
public class CartsetResponse {
	
    private PermissionedCartset permissionedCartset;

    @XmlElement(required = true)
	public PermissionedCartset getPermissionedCartset() {
		return permissionedCartset;
	}
	public void setPermissionedCartset(PermissionedCartset permissionedCartset_) {
		permissionedCartset = permissionedCartset_;
	}
	
}