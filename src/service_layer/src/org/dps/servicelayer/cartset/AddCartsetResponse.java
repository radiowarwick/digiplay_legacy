package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.PROPERTY)
public class AddCartsetResponse {
	
    private PermissionedCartset permissionedCartset;

    public AddCartsetResponse() {
    	
    }
    
    public AddCartsetResponse(AddCartsetRequest request) {
    	
    }
    
    @XmlElement(required = true)
	public PermissionedCartset getPermissionedCartset() {
		return permissionedCartset;
	}
	public void setPermissionedCartset(PermissionedCartset permissionedCartset_) {
		permissionedCartset = permissionedCartset_;
	}
	
}