package org.dps.servicelayer.common;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;


@XmlAccessorType(XmlAccessType.PROPERTY)
public abstract class PermissionedItem {
	
    private boolean read;
	private boolean write;
 	private boolean execute;
	
	@XmlElement(required = true)
	public boolean isRead() {
		return read;
	}
	public void setRead(boolean read_) {
		read = read_;
	}
	
	@XmlElement(required = true)
	public boolean isWrite() {
		return write;
	}
	public void setWrite(boolean write_) {
		write = write_;
	}
	
	@XmlElement(required = true)
	public boolean isExecute() {
		return execute;
	}
	public void setExecute(boolean execute_) {
		execute = execute_;
	}
}
