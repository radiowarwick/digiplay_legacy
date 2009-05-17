package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.NONE)
public class AddCartStyleRequest {
	
	private String name;
	private String description;
	
	@XmlElement(required = true)
	public String getName() {
		return name;
	}
	public void setName(String name_) {
		name = name_;
	}
	
	@XmlElement(required = false)
	public String getDescription() {
		return description;
	}
	public void setDescription(String description_) {
		description = description_;
	}
		
}
