package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.Namespaces;
import org.dps.servicelayer.dto.Cartwall;

@XmlAccessorType(XmlAccessType.NONE)
public class AddCartwallResponse {
	
	private Long cartsetID;
    private Cartwall cartwall;

	public AddCartwallResponse() {
    	
    }
    
    public AddCartwallResponse(AddCartwallRequest request) {
    	cartsetID = request.getCartsetID();
    }
    
    @XmlElement(required = true)
	public Long getCartsetID() {
		return cartsetID;
	}
	public void setCartsetID(Long cartsetID_) {
		cartsetID = cartsetID_;
	}
	
    @XmlElement(required = true, namespace = Namespaces.DTO)
	public Cartwall getCartwall() {
		return cartwall;
	}

	public void setCartwall(Cartwall cartwall_) {
		cartwall = cartwall_;
	}
	
}