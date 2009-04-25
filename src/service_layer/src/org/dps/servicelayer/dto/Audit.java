package org.dps.servicelayer.dto;

import java.util.Calendar;
import java.util.GregorianCalendar;

import javax.persistence.Column;
import javax.persistence.MappedSuperclass;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.persistence.Version;

import org.hibernate.annotations.Generated;
import org.hibernate.annotations.GenerationTime;


@MappedSuperclass
public abstract class Audit {
	
	@Column(name="last_modified", insertable = true, updatable = true)
	@Version()
	@Generated(GenerationTime.NEVER)
	@Temporal(TemporalType.TIMESTAMP)
	private Calendar lastUpdated;

	/**
	 * @return the lastUpdated
	 */
	public Calendar getLastUpdated() {
		return lastUpdated;
	}
	/**
	 * @param lastUpdated the lastUpdated to set
	 */
	public void setLastUpdated(Calendar lastUpdated) {
		this.lastUpdated = lastUpdated;
	}

}
