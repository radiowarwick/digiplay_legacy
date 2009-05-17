package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.Namespaces;
import org.dps.servicelayer.dto.CartStyle;

@XmlAccessorType(XmlAccessType.NONE)
public class GetCartStyleResponse {
	
    private CartStyle cartStyle;

    public GetCartStyleResponse() {
    	
    }
    
    public GetCartStyleResponse(GetCartStyleRequest request) {
    	
    }

	@XmlElement(required = true, namespace = Namespaces.DTO)
	public CartStyle getCartStyle() {
		return cartStyle;
	}
	public void setCartStyle(CartStyle cartStyle_) {
		cartStyle = cartStyle_;
	}
    
	
}