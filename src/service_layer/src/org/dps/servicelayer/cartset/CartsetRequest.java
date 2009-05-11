package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.PROPERTY)
public class CartsetRequest {
    private Long cartsetID;

    @XmlElement(required = true)
	public Long getCartsetID() {
		return cartsetID;
	}

	public void setCartsetID(Long cartsetID_) {
		cartsetID = cartsetID_;
	}
}
