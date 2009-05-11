package org.dps.servicelayer.common;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlTransient;

import org.dps.servicelayer.dto.File;


@XmlAccessorType(XmlAccessType.PROPERTY)
public abstract class PermissionedItem<T extends File> {
	
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
	
	@XmlTransient
	public abstract T getItem();
	public abstract void setItem(T item_);
}
