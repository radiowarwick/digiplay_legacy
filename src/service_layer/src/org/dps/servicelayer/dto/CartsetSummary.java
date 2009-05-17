package org.dps.servicelayer.dto;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;


@XmlAccessorType(XmlAccessType.NONE)
public class CartsetSummary extends File {
	
	//Cartset
	private String name;
	private String description;
	
	public CartsetSummary() {
		
	}

	public CartsetSummary(Cartset cartset) {
		//cartset
		this.name = cartset.getName();
		this.description = cartset.getDescription();
		//file
		this.setFileID(cartset.getFileID());
		this.setParentID(cartset.getParentID());
		this.setFilename(cartset.getFilename());
		this.setOwnerGroup(cartset.getOwnerGroup());
		this.setOwner(cartset.getOwner());
		this.setEntityType(cartset.getEntityType());
		this.setUserRead(cartset.getUserRead());
		this.setUserWrite(cartset.getUserWrite());
		this.setUserExecute(cartset.getUserExecute());
		this.setGroupRead(cartset.getGroupRead());
		this.setGroupWrite(cartset.getGroupWrite());
		this.setGroupExecute(cartset.getGroupExecute());
		this.setAllRead(cartset.getAllRead());
		this.setAllWrite(cartset.getAllWrite());
		this.setAllExecute(cartset.getAllExecute());
		this.setCreated(cartset.getCreated());
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
