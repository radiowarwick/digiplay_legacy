package org.dps.servicelayer.dto;

import java.util.HashSet;
import java.util.Set;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToMany;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlTransient;

@Entity
@Table(name="t_group")
@XmlAccessorType(XmlAccessType.NONE)
public class Group extends Audit{
	
	@Column(name="group_id")
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	private Long groupID;
	
	@Column(name="name")
	private String name;
	
	@Column(name="description")
	private String description;
	
	@ManyToMany(cascade={CascadeType.PERSIST, CascadeType.MERGE},
			mappedBy="groups",
			targetEntity= User.class)
	private Set<User> users = new HashSet<User>();

	
	/**
	 * @return the groupID
	 */
	@XmlElement(required = true)
	public Long getGroupID() {
		return groupID;
	}
	/**
	 * @param groupID the groupID to set
	 */
	public void setGroupID(Long groupID) {
		this.groupID = groupID;
	}

	/**
	 * @return the name
	 */
	@XmlElement(required = true)
	public String getName() {
		return name;
	}
	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		this.name = name;
	}

	/**
	 * @return the description
	 */
	@XmlElement(required = true)
	public String getDescription() {
		return description;
	}
	/**
	 * @param description the description to set
	 */
	public void setDescription(String description) {
		this.description = description;
	}

	/**
	 * @return the users
	 */
	@XmlTransient
	public Set<User> getUsers() {
		return users;
	}
	/**
	 * @param users the users to set
	 */
	public void setUsers(Set<User> users) {
		this.users = users;
	}
	
	public String toString() {
		return groupID + ":" + name;
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((groupID == null) ? 0 : groupID.hashCode());
		return result;
	}
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Group other = (Group) obj;
		if (groupID == null) {
			if (other.groupID != null)
				return false;
		} else if (!groupID.equals(other.groupID))
			return false;
		return true;
	}
	
}
