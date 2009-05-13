package org.dps.servicelayer.cartset;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;

@XmlAccessorType(XmlAccessType.PROPERTY)
public class AddCartsetRequest {
    private String name;
    private String description;
    private Long parentID;
    private String filename;
    private Long groupID;
	private Boolean userRead = Boolean.TRUE;
	private Boolean userWrite = Boolean.TRUE;
	private Boolean userExecute = Boolean.TRUE;
	private Boolean groupRead = Boolean.FALSE;
	private Boolean groupWrite = Boolean.FALSE;
	private Boolean groupExecute = Boolean.FALSE;
	private Boolean allRead = Boolean.FALSE;
	private Boolean allWrite = Boolean.FALSE;
	private Boolean allExecute = Boolean.FALSE;
	
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
	@XmlElement(required = true)
	public Long getParentID() {
		return parentID;
	}
	public void setParentID(Long parentID_) {
		parentID = parentID_;
	}
	@XmlElement(required = false)
	public String getFilename() {
		return filename;
	}
	public void setFilename(String filename_) {
		filename = filename_;
	}
	@XmlElement(required = false)
	public Long getGroupID() {
		return groupID;
	}
	public void setGroupID(Long groupID_) {
		groupID = groupID_;
	}
	@XmlElement(required = false)
	public Boolean getUserRead() {
		return userRead;
	}
	public void setUserRead(Boolean userRead_) {
		userRead = userRead_;
	}
	@XmlElement(required = false)
	public Boolean getUserWrite() {
		return userWrite;
	}
	public void setUserWrite(Boolean userWrite_) {
		userWrite = userWrite_;
	}
	@XmlElement(required = false)
	public Boolean getUserExecute() {
		return userExecute;
	}
	public void setUserExecute(Boolean userExecute_) {
		userExecute = userExecute_;
	}
	@XmlElement(required = false)
	public Boolean getGroupRead() {
		return groupRead;
	}
	public void setGroupRead(Boolean groupRead_) {
		groupRead = groupRead_;
	}
	@XmlElement(required = false)
	public Boolean getGroupWrite() {
		return groupWrite;
	}
	public void setGroupWrite(Boolean groupWrite_) {
		groupWrite = groupWrite_;
	}
	@XmlElement(required = false)
	public Boolean getGroupExecute() {
		return groupExecute;
	}
	public void setGroupExecute(Boolean groupExecute_) {
		groupExecute = groupExecute_;
	}
	@XmlElement(required = false)
	public Boolean getAllRead() {
		return allRead;
	}
	public void setAllRead(Boolean allRead_) {
		allRead = allRead_;
	}
	@XmlElement(required = false)
	public Boolean getAllWrite() {
		return allWrite;
	}
	public void setAllWrite(Boolean allWrite_) {
		allWrite = allWrite_;
	}
	@XmlElement(required = false)
	public Boolean getAllExecute() {
		return allExecute;
	}
	public void setAllExecute(Boolean allExecute_) {
		allExecute = allExecute_;
	}
	
    
}
