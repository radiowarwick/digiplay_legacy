package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.NONE)
public class DeleteCartStylePropertyRequest {
	
	private Long cartStyleID;
	private String name;
	private String property;
	
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
	
	@XmlElement(required = true)
	public String getProperty() {
		return property;
	}
	public void setProperty(String property_) {
		property = property_;
	}
	
}
