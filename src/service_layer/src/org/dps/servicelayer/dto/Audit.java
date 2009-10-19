package org.dps.servicelayer.dto;

import java.util.Calendar;

import javax.persistence.Column;
import javax.persistence.MappedSuperclass;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.persistence.Version;
import javax.xml.bind.annotation.XmlTransient;

import org.hibernate.annotations.Generated;
import org.hibernate.annotations.GenerationTime;


@MappedSuperclass
public abstract class Audit implements IMakeSafe {
	
	@Column(name="last_modified", insertable = true, updatable = true)
	@Version()
	@Generated(GenerationTime.NEVER)
	@Temporal(TemporalType.TIMESTAMP)
	private Calendar lastUpdated;

	/**
	 * @return the lastUpdated
	 */
	@XmlTransient
	public Calendar getLastUpdated() {
		return lastUpdated;
	}
	/**
	 * @param lastUpdated the lastUpdated to set
	 */
	protected void setLastUpdated(Calendar lastUpdated) {
		this.lastUpdated = lastUpdated;
	}

	public void makeSafe() {
		
	}
}