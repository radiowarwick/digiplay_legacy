package org.dps.servicelayer.cartset.wrappers;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "CartsetRequest", propOrder = {
    "cartsetID"
})
public class CartsetRequest {
	@XmlElement(required = true)
    private Long cartsetID;

	public Long getCartsetID() {
		return cartsetID;
	}

	public void setCartsetID(Long cartsetID_) {
		cartsetID = cartsetID_;
	}
}
