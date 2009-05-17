package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.NONE)
public class DeleteCartStyleRequest {
	
	private Long cartStyleID;
	private String name;
	
	@XmlElement(required = false)
	public Long getCartStyleID() {
		return cartStyleID;
	}
	public void setCartStyleID(Long cartStyleID_) {
		cartStyleID = cartStyleID_;
	}
	
	@XmlElement(required = false)
	public String getName() {
		return name;
	}
	public void setName(String name_) {
		name = name_;
	}
	
		
}
