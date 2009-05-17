package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.Namespaces;
import org.dps.servicelayer.dto.CartStyle;

@XmlAccessorType(XmlAccessType.NONE)
public class UpdateCartStyleResponse {
	
    private CartStyle cartStyle;

    public UpdateCartStyleResponse() {
    	
    }
    
    public UpdateCartStyleResponse(UpdateCartStyleRequest request) {
    	
    }


	@XmlElement(required = true, namespace = Namespaces.DTO)
	public CartStyle getCartStyle() {
		return cartStyle;
	}
	public void setCartStyle(CartStyle cartStyle_) {
		cartStyle = cartStyle_;
	}
    
	
}