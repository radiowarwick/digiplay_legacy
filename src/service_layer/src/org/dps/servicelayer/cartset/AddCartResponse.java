package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

import org.dps.servicelayer.Namespaces;
import org.dps.servicelayer.dto.CartAudio;

@XmlAccessorType(XmlAccessType.NONE)
public class AddCartResponse {
	
	private Long cartwallID;
    private CartAudio cart;

    public AddCartResponse() {
    	
    }
    
    public AddCartResponse(AddCartRequest request) {
    	cartwallID = request.getCartwallID();
    }

    @XmlElement(required = true)
	public Long getCartwallID() {
		return cartwallID;
	}
	public void setCartwallID(Long cartwallID_) {
		cartwallID = cartwallID_;
	}

	@XmlElement(required = true, namespace = Namespaces.DTO)
	public CartAudio getCart() {
		return cart;
	}
	public void setCart(CartAudio cart_) {
		cart = cart_;
	}
    
	
}