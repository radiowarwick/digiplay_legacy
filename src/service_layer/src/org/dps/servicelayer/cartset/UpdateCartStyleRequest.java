package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.NONE)
public class UpdateCartStyleRequest {
	
	private Long cartStyleID;
	private String name;
	private String description;
	
	@XmlElement(required = true)
	public Long getCartStyleID() {
		return cartStyleID;
	}
	public void setCartStyleID(Long cartStyleID_) {
		cartStyleID = cartStyleID_;
	}
	
	@XmlElement(required = true)
	public String getName() {
		return name;
	}
	public void setName(String name_) {
		name = name_;
	}
	
	@XmlElement(required = true)
	public String getDescription() {
		return description;
	}
	public void setDescription(String description_) {
		description = description_;
	}
		
}
