package org.dps.servicelayer.common;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;

import org.dps.servicelayer.dto.File;


@XmlAccessorType(XmlAccessType.PROPERTY)
public abstract class SummaryItem<T extends File> extends File {
	
	public abstract void build(T item);
	
}
